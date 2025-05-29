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
    }

    // Log kill
    if (heroId != -1) {
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
    } else {
        std::cerr << "Hero not found in database.\n";
    }

    sqlite3_close(db);
}
