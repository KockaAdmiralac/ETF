package rs.ac.bg.etf.rm2.projekat;

import java.awt.GridLayout;
import java.io.IOException;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.JTextField;

import com.ireasoning.protocol.snmp.SnmpSession;
import com.ireasoning.protocol.snmp.SnmpTableModel;
import com.ireasoning.protocol.snmp.SnmpTarget;

public class Variant9 extends Variant {
	private static final long serialVersionUID = 7170313970878567134L;
	private SnmpSession session = null;
	
	public Variant9() {
		// Build UI.
		JTabbedPane tabs = new JTabbedPane();
		JPanel inputPanel = new JPanel(new GridLayout(1, 3));
		JTextField textField = new JTextField();
		JButton button = new JButton("Otvori");
		inputPanel.add(new JLabel("IP adresa:"));
		inputPanel.add(textField);
		inputPanel.add(button);
		button.addActionListener(ae -> {
			try {
				// Set up connection.
				SnmpTarget target = new SnmpTarget(textField.getText(), PORT, COMMUNITY, COMMUNITY, 1);
				session = new SnmpSession(target);
				SnmpTableModel tcpTable = getTable(session, "tcpConnTable", 5);
				SnmpTableModel udpTable = getTable(session, "udpTable", 5);
				// Table UI
				JPanel tablePanel = new JPanel();
				tablePanel.setLayout(new GridLayout(0, 2));
				JTable tcpTableView = new JTable(tcpTable);
				JTable udpTableView = new JTable(udpTable);
				renameColumn(tcpTableView, "tcpConnState", "State");
				renameColumn(tcpTableView, "tcpConnLocalAddress", "Local Address");
				renameColumn(tcpTableView, "tcpConnLocalPort", "Local Port");
				renameColumn(tcpTableView, "tcpConnRemAddress", "Remote Address");
				renameColumn(tcpTableView, "tcpConnRemPort", "Remote Port");
				renameColumn(udpTableView, "udpLocalAddress", "Address");
				renameColumn(udpTableView, "udpLocalPort", "Port");
				tcpTableView.setAutoCreateColumnsFromModel(true);
				udpTableView.setAutoCreateColumnsFromModel(true);
				JScrollPane tcpTablePane = new JScrollPane(tcpTableView);
				JScrollPane udpTablePane = new JScrollPane(udpTableView);
				tablePanel.add(tcpTablePane);
				tablePanel.add(udpTablePane);
				tabs.addTab(session.snmpGetRequest("sysName").getVarBind(0).getValue().toString(), tablePanel);
			} catch (IOException e) {
				e.printStackTrace();
			} finally {
				if (session != null) {
					session.close();
				}
			}
		});
		tabs.addTab("Input", inputPanel);
		getContentPane().add(tabs);
		pack();
	}
	
}
