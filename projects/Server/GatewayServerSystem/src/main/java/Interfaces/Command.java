package Interfaces;

import com.sun.media.sound.InvalidDataException;
import database_manager.AdminSQLManager;
import database_manager.MongoDBManager;

public interface Command {
    void exec(AdminSQLManager adminSQLManager, MongoDBManager mongoDBManager) throws InvalidDataException;
}
