package rs.ac.bg.etf.rm2.projekat;

import java.awt.GridLayout;
import java.io.IOException;
import java.text.ParseException;

import javax.swing.JScrollPane;
import javax.swing.JTable;

import com.ireasoning.protocol.snmp.SnmpSession;
import com.ireasoning.protocol.snmp.SnmpTableModel;
import com.ireasoning.protocol.snmp.SnmpTarget;

public class Variant4 extends Variant {
	private static final long serialVersionUID = 7170313970878567134L;
	private SnmpSession session = null;
	
	public Variant4() {
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
			SnmpTableModel peerTable = getTable(session, "bgpPeerTable", 10);
			
			// Build UI.
			setLayout(new GridLayout());
			JTable peerTableView = new JTable(peerTable);
			removeColumn(peerTableView, "bgpPeerAdminStatus");
			removeColumn(peerTableView, "bgpPeerLocalAddr");
			removeColumn(peerTableView, "bgpPeerLocalPort");
			removeColumn(peerTableView, "bgpPeerInTotalMessages");
			removeColumn(peerTableView, "bgpPeerOutTotalMessages");
			removeColumn(peerTableView, "bgpPeerLastError");
			removeColumn(peerTableView, "bgpPeerFsmEstablishedTransitions");
			removeColumn(peerTableView, "bgpPeerFsmEstablishedTime");
			removeColumn(peerTableView, "bgpPeerConnectRetryInterval");
			removeColumn(peerTableView, "bgpPeerHoldTime");
			removeColumn(peerTableView, "bgpPeerHoldTimeConfigured");
			removeColumn(peerTableView, "bgpPeerKeepAliveConfigured");
			removeColumn(peerTableView, "bgpPeerMinASOriginationInterval");
			removeColumn(peerTableView, "bgpPeerMinRouteAdvertisementInterval");
			renameColumn(peerTableView, "bgpPeerIdentifier", "ID");
			renameColumn(peerTableView, "bgpPeerState", "State");
			renameColumn(peerTableView, "bgpPeerNegotiatedVersion", "4");
			renameColumn(peerTableView, "bgpPeerRemoteAddr", "Remote Address");
			renameColumn(peerTableView, "bgpPeerRemotePort", "Remote Port");
			renameColumn(peerTableView, "bgpPeerRemoteAs", "Remote AS");
			renameColumn(peerTableView, "bgpPeerInUpdates", "Updates Received");
			renameColumn(peerTableView, "bgpPeerOutUpdates", "Updates Sent");
			renameColumn(peerTableView, "bgpPeerKeepAlive", "Keepalive");
			renameColumn(peerTableView, "bgpPeerInUpdateElapsedTime", "Elapsed time");
			peerTableView.setAutoCreateColumnsFromModel(true);
			JScrollPane peerTablePane = new JScrollPane(peerTableView);
			getContentPane().add(peerTablePane);
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
