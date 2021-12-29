package rs.ac.bg.etf.rm2.projekat;

import java.io.IOException;

import javax.swing.JFrame;
import javax.swing.JTable;

import com.ireasoning.protocol.snmp.SnmpOID;
import com.ireasoning.protocol.snmp.SnmpSession;
import com.ireasoning.protocol.snmp.SnmpTableModel;

public abstract class Variant extends JFrame {
	private static final long serialVersionUID = -5984454657696028884L;
	public static final String COMMUNITY = "si2019";
	public static final String R1_HOST = "192.168.10.1";
	public static final String R2_HOST = "192.168.20.1";
	public static final String R3_HOST = "192.168.30.1";
	public static final int PORT = 161;
	public static final int LISTENER_PORT = 1620;
	public static final String[] HOSTS = {R1_HOST, R2_HOST, R3_HOST};

	public Variant() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	protected void removeColumn(JTable table, String column) {
		table.removeColumn(table.getColumn(column));
	}

	protected void renameColumn(JTable table, String column, String name) {
		table.getColumn(column).setHeaderValue(name);
	}

	protected SnmpTableModel getTable(SnmpSession session, String tableName, int pollingInterval) throws IOException {
		SnmpTableModel table;
		table = session.snmpGetTable(tableName);
		if (table == null) {
			throw new RuntimeException("Failed to load MIB2.");
		}
		SnmpOID authFailureOID = table.getAuthFailureOID();
		if (authFailureOID != null) {
			throw new RuntimeException("An authentication failure occurred.");
		}
		table.setTranslateValue(true);
		table.startPolling(pollingInterval);
		return table;
	}
}
