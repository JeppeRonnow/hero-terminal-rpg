#include "DatabaseManager.hpp"


DatabaseManager::DatabaseManager(std::string databaseFilePath){
    this->databaseFilePath = databaseFilePath;

}


void DatabaseManager::saveHero(const Hero& hero) {
    sqlite3* db;
    if (sqlite3_open(databaseFilePath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Step 1: INSERT if hero doesn't exist
    const char* insertSQL = R"(
        INSERT OR IGNORE INTO Heroes (name, hp, strength, level, xp, gold)
        VALUES (?, ?, ?, ?, ?, ?);
    )";

    sqlite3_stmt* insertStmt;
    if (sqlite3_prepare_v2(db, insertSQL, -1, &insertStmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(insertStmt, 1, hero.getName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(insertStmt, 2, hero.getHP());
        sqlite3_bind_int(insertStmt, 3, hero.getStrength());
        sqlite3_bind_int(insertStmt, 4, hero.getLevel());
        sqlite3_bind_int(insertStmt, 5, hero.getXP());
        sqlite3_bind_int(insertStmt, 6, hero.getGold());

        sqlite3_step(insertStmt);
        sqlite3_finalize(insertStmt);
    } else {
        std::cerr << "Error preparing INSERT statement: " << sqlite3_errmsg(db) << std::endl;
    }

    // Step 2: UPDATE stats for that hero
    const char* updateSQL = R"(
        UPDATE Heroes
        SET hp = ?, strength = ?, level = ?, xp = ?, gold = ?
        WHERE name = ?;
    )";

    sqlite3_stmt* updateStmt;
    if (sqlite3_prepare_v2(db, updateSQL, -1, &updateStmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(updateStmt, 1, hero.getHP());
        sqlite3_bind_int(updateStmt, 2, hero.getStrength());
        sqlite3_bind_int(updateStmt, 3, hero.getLevel());
        sqlite3_bind_int(updateStmt, 4, hero.getXP());
        sqlite3_bind_int(updateStmt, 5, hero.getGold());
        sqlite3_bind_text(updateStmt, 6, hero.getName().c_str(), -1, SQLITE_TRANSIENT);

        sqlite3_step(updateStmt);
        sqlite3_finalize(updateStmt);
    } else {
        std::cerr << "Error preparing UPDATE statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_close(db);
}

Hero DatabaseManager::loadHero(const std::string& heroName) const {
    sqlite3* db;
    if (sqlite3_open(databaseFilePath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error("Failed to open database");
    }

    const char* sql = R"(
        SELECT hp, strength, level, xp, gold
        FROM Heroes
        WHERE name = ?;
    )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        throw std::runtime_error("Failed to prepare SQL");
    }

    sqlite3_bind_text(stmt, 1, heroName.c_str(), -1, SQLITE_TRANSIENT);

    Hero hero("", 0, 0, 0, 0, 0);  // fallback default

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int hp = sqlite3_column_int(stmt, 0);
        int strength = sqlite3_column_int(stmt, 1);
        int level = sqlite3_column_int(stmt, 2);
        int xp = sqlite3_column_int(stmt, 3);
        int gold = sqlite3_column_int(stmt, 4);

        hero = Hero(heroName, xp, level, hp, strength, gold);

    } else {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        throw std::runtime_error("Hero not found in database");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return hero;
}

void DatabaseManager::logKill(const std::string& heroName, const std::string& weaponName) {
    sqlite3* db;
    if (sqlite3_open(databaseFilePath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    int heroId = -1;
    int weaponId = -1;

    // Get heroId
    std::string getHeroIdSQL = "SELECT id FROM Heroes WHERE name = ?;";
    sqlite3_stmt* heroStmt;
    if (sqlite3_prepare_v2(db, getHeroIdSQL.c_str(), -1, &heroStmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(heroStmt, 1, heroName.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(heroStmt) == SQLITE_ROW) {
            heroId = sqlite3_column_int(heroStmt, 0);
        }
    }
    sqlite3_finalize(heroStmt);

    // If hero does not exist, assign a custom ID and insert them into the database
    if (heroId == -1) {
        std::cerr << "Hero '" << heroName << "' not found in database. Adding hero...\n";

        // Find the maximum existing ID
        std::string getMaxIdSQL = "SELECT MAX(id) FROM Heroes;";
        sqlite3_stmt* maxIdStmt;
        int maxId = 0;
        if (sqlite3_prepare_v2(db, getMaxIdSQL.c_str(), -1, &maxIdStmt, nullptr) == SQLITE_OK) {
            if (sqlite3_step(maxIdStmt) == SQLITE_ROW) {
                maxId = sqlite3_column_int(maxIdStmt, 0);
            }
        }
        sqlite3_finalize(maxIdStmt);

        heroId = maxId + 1; // Assign the next ID

        std::string insertHeroSQL = R"(
            INSERT INTO Heroes (id, name, hp, strength, level, xp, gold)
            VALUES (?, ?, 100, 10, 1, 0, 0);
        )";
        sqlite3_stmt* insertHeroStmt;
        if (sqlite3_prepare_v2(db, insertHeroSQL.c_str(), -1, &insertHeroStmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_int(insertHeroStmt, 1, heroId);
            sqlite3_bind_text(insertHeroStmt, 2, heroName.c_str(), -1, SQLITE_TRANSIENT);
            if (sqlite3_step(insertHeroStmt) == SQLITE_DONE) {
                std::cout << "Hero '" << heroName << "' added to database with ID: " << heroId << "\n";
            }
        }
        sqlite3_finalize(insertHeroStmt);

        if (heroId == -1) {
            std::cerr << "Failed to add hero to database.\n";
            sqlite3_close(db);
            return;
        }
    }

    // Only try to get weaponId if a weapon name was given
    if (!weaponName.empty()) {
        std::string getWeaponIdSQL = "SELECT id FROM Weapons WHERE name = ?;";
        sqlite3_stmt* weaponStmt;
        if (sqlite3_prepare_v2(db, getWeaponIdSQL.c_str(), -1, &weaponStmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(weaponStmt, 1, weaponName.c_str(), -1, SQLITE_TRANSIENT);
            if (sqlite3_step(weaponStmt) == SQLITE_ROW) {
                weaponId = sqlite3_column_int(weaponStmt, 0);
            }
        }
        sqlite3_finalize(weaponStmt);

        if (weaponId == -1) {
            std::cerr << "Weapon '" << weaponName << "' not found in database.\n";
        }
    }

    // Log kill
    std::string insertKillSQL = "INSERT INTO Kills (heroId, weaponId) VALUES (?, ?);";
    sqlite3_stmt* insertStmt;
    if (sqlite3_prepare_v2(db, insertKillSQL.c_str(), -1, &insertStmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(insertStmt, 1, heroId);
        if (weaponId != -1)
            sqlite3_bind_int(insertStmt, 2, weaponId);
        else
            sqlite3_bind_null(insertStmt, 2);

        if (sqlite3_step(insertStmt) != SQLITE_DONE) {
            std::cerr << "Error logging kill: " << sqlite3_errmsg(db) << std::endl;
        }
    }
    sqlite3_finalize(insertStmt);

    sqlite3_close(db);
}

void DatabaseManager::saveHeroInventory(const Hero& hero) {
    sqlite3* db;
    if (sqlite3_open(databaseFilePath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Failed to open DB: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    // Step 1: find heroId
    int heroId = -1;
    {
        std::string sql = "SELECT id FROM Heroes WHERE name = ?;";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, hero.getName().c_str(), -1, SQLITE_TRANSIENT);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                heroId = sqlite3_column_int(stmt, 0);
            }
        }
        sqlite3_finalize(stmt);
    }

    if (heroId == -1) {
        std::cerr << "Hero not found in DB\n";
        sqlite3_close(db);
        return;
    }

    // Step 2: Prepare the INSERT statement once
    std::string insertSQL = R"(
        INSERT INTO HeroWeapons (heroId, weaponId, instanceId, durabilityLeft)
        VALUES (?, ?, ?, ?);
    )";
    sqlite3_stmt* insertStmt;
    if (sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &insertStmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing INSERT statement: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return;
    }

    // Step 3: Iterate over the inventory and save each weapon
    int instanceId = 1; // Start instanceId at 1 for each hero
    for (const Weapon& w : hero.getInventory()) {
        // find weaponId
        int weaponId = -1;
        {
            std::string sql = "SELECT id FROM Weapons WHERE name = ?;";
            sqlite3_stmt* stmt;
            if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(stmt, 1, w.getName().c_str(), -1, SQLITE_TRANSIENT);
                if (sqlite3_step(stmt) == SQLITE_ROW) {
                    weaponId = sqlite3_column_int(stmt, 0);
                }
            }
            sqlite3_finalize(stmt);
        }

        if (weaponId == -1) {
            std::cerr << "Weapon '" << w.getName() << "' not found in DB\n";
            continue;
        }

        // Bind values and execute the INSERT statement
        sqlite3_bind_int(insertStmt, 1, heroId);
        sqlite3_bind_int(insertStmt, 2, weaponId);
        sqlite3_bind_int(insertStmt, 3, instanceId++);
        sqlite3_bind_int(insertStmt, 4, w.getDurability());

        if (sqlite3_step(insertStmt) != SQLITE_DONE) {
            std::cerr << "Error saving inventory weapon: " << sqlite3_errmsg(db) << "\n";
        }

        // Reset the statement for the next iteration
        sqlite3_reset(insertStmt);
    }

    // Finalize the prepared statement
    sqlite3_finalize(insertStmt);
    sqlite3_close(db);
}

void DatabaseManager::loadHeroInventory(Hero& hero) const {
    sqlite3* db;
    if (sqlite3_open(databaseFilePath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Failed to open DB: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    // Get heroId
    int heroId = -1;
    {
        std::string sql = "SELECT id FROM Heroes WHERE name = ?;";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, hero.getName().c_str(), -1, SQLITE_TRANSIENT);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                heroId = sqlite3_column_int(stmt, 0);
            }
        }
        sqlite3_finalize(stmt);
    }

    if (heroId == -1) {
        std::cerr << "Hero not found in DB\n";
        sqlite3_close(db);
        return;
    }

    // Load weapons from HeroWeapons
    std::string sql = R"(
        SELECT w.name, w.damage, w.multiplier, hw.durabilityLeft
        FROM HeroWeapons hw
        JOIN Weapons w ON hw.weaponId = w.id
        WHERE hw.heroId = ?;
    )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, heroId);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            int damage = sqlite3_column_int(stmt, 1);
            int multiplier = sqlite3_column_int(stmt, 2);
            int durability = sqlite3_column_int(stmt, 3);

            Weapon w(name, damage, multiplier, durability);
            hero.addWeaponToInventory(w);
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
