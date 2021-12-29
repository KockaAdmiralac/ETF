package rs.ac.bg.etf.rm2.projekat;

import java.awt.Color;
import java.awt.Component;
import java.awt.GridLayout;
import java.io.IOException;
import java.text.ParseException;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableCellRenderer;

import com.ireasoning.protocol.snmp.SnmpOctetString;
import com.ireasoning.protocol.snmp.SnmpSession;
import com.ireasoning.protocol.snmp.SnmpTableModel;
import com.ireasoning.protocol.snmp.SnmpTarget;

public class Variant5 extends Variant {
	private static final long serialVersionUID = 7093241976023291110L;
	private SnmpSession session = null;
	
	static class CustomTableCellRenderer extends DefaultTableCellRenderer {
		private static final long serialVersionUID = -2121671273780622539L;
		@Override
		public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected,
				boolean hasFocus, int row, int column) {
			final Component c = super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, column);
			if (((String)table.getModel().getValueAt(row, 12)).equals("true")) {
				c.setBackground(Color.GREEN);
			} else {
				c.setBackground(Color.RED);
			}
			return c;
		}
	}
	
	public Variant5() {
		try {
			SnmpSession.loadMib("BGP4-MIB");
		} catch (IOException | ParseException e1) {
			e1.printStackTrace();
			return;
		}
		try {
			// Set up connection.
			SnmpTarget target = new SnmpTarget(R1_HOST, PORT, COMMUNITY, COMMUNITY, 1);
			session = new SnmpSession(target);
			SnmpTableModel bgpTable = getTable(session, "bgp4PathAttrTable", 10);
			
			// Build UI.
			setLayout(new GridLayout());
			JTable bgpTableView = new JTable(bgpTable);
			bgpTableView.setAutoCreateColumnsFromModel(true);
			removeColumn(bgpTableView, "bgp4PathAttrPeer");
			removeColumn(bgpTableView, "bgp4PathAttrCalcLocalPref");
			removeColumn(bgpTableView, "bgp4PathAttrBest");
			removeColumn(bgpTableView, "bgp4PathAttrUnknown");
			renameColumn(bgpTableView, "bgp4PathAttrIpAddrPrefixLen", "Prefix Length");
			renameColumn(bgpTableView, "bgp4PathAttrIpAddrPrefix", "Prefix");
			renameColumn(bgpTableView, "bgp4PathAttrOrigin", "Origin");
			renameColumn(bgpTableView, "bgp4PathAttrNextHop", "Next Hop");
			renameColumn(bgpTableView, "bgp4PathAttrMultiExitDisc", "MED");
			renameColumn(bgpTableView, "bgp4PathAttrLocalPref", "Local Preference");
			renameColumn(bgpTableView, "bgp4PathAttrAtomicAggregate", "Atomic Aggregate");
			renameColumn(bgpTableView, "bgp4PathAttrAggregatorAS", "Aggregator AS");
			renameColumn(bgpTableView, "bgp4PathAttrAggregatorAddr", "Aggregator Address");
			bgpTableView.setDefaultRenderer(Object.class, new CustomTableCellRenderer());
			bgpTableView.getColumn("bgp4PathAttrASPathSegment").setCellRenderer((table, value, isSelected, hasFocus, row, column) -> {
				JPanel pane = new JPanel();
				SnmpOctetString val = (SnmpOctetString) bgpTable.get(row, column+1).getValue();
				byte[] bytes = val.getValue();
				StringBuilder asPath = new StringBuilder();
				byte length = bytes[1];
				for (int i = 0; i < length; ++i) {
					asPath.append(String.valueOf(bytes[2 + i * 2] * 256 + bytes[2 + i * 2 + 1]));
					asPath.append(" ");
				}
				JLabel label = new JLabel(asPath.toString());
				if (((String)bgpTable.getValueAt(row, 12)).equals("true")) {
					pane.setBackground(Color.GREEN);
				} else {
					pane.setBackground(Color.RED);
				}
				pane.add(label);
				label.revalidate();
				label.repaint();
				return pane;
			});
			renameColumn(bgpTableView, "bgp4PathAttrASPathSegment", "AS Path");
			bgpTableView.setRowHeight(24);
			JScrollPane bgpTablePane = new JScrollPane(bgpTableView);
			getContentPane().add(bgpTablePane);
			pack();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (session != null) {
				session.close();
			}
		}
	}
}
