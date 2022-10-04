package rs.ac.bg.etf.pia.petshop2021.util;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;

public class DB {
    private static DB instance;
    private static final int MAX_CON = 5;
    private static final Connection[] bafer = new Connection[MAX_CON];
    private int first = 0, last = 0, free = MAX_CON;

    private DB() {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            for (int i = 0; i < MAX_CON; i++) {
                bafer[i] = DriverManager.getConnection("jdbc:mysql://localhost:3306/petshop2021?useSSL=false", "is1", "tubic");
            }
        } catch (ClassNotFoundException | SQLException ex) {
            Logger.getLogger(DB.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public static DB getInstance() {
        if (instance == null)
            instance = new DB();
        return instance;
    }

    public synchronized Connection getConnection() {
        if (free == 0)
            return null;
        free--;
        Connection con = bafer[first];
        first = (first + 1) % MAX_CON;
        return con;
    }

    public synchronized void putConnection(Connection con) {
        if (con == null)
            return;
        free++;
        bafer[last] = con;
        last = (last + 1) % MAX_CON;
    }
}
