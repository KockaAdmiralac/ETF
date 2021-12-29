package rs.ac.bg.etf.rm2.projekat;

import java.awt.GridLayout;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.swing.JLabel;
import javax.swing.JPanel;

import com.ireasoning.protocol.Msg;
import com.ireasoning.protocol.snmp.SnmpPdu;
import com.ireasoning.protocol.snmp.SnmpPoller;
import com.ireasoning.protocol.snmp.SnmpSession;
import com.ireasoning.protocol.snmp.SnmpTarget;
import com.ireasoning.protocol.snmp.SnmpVarBind;

public class Variant7 extends Variant {
	private static final long serialVersionUID = 7693828790375508738L;
	private SnmpSession session = null;
	private List<Map<String, JLabel>> data = new ArrayList<>();
	private static final String[] PROPERTIES = new String[] {
		".1.3.6.1.2.1.11.1",
		".1.3.6.1.2.1.11.2",
		".1.3.6.1.2.1.11.4",
		".1.3.6.1.2.1.11.15",
		".1.3.6.1.2.1.11.17",
		".1.3.6.1.2.1.11.29"
	};
	private static final String[] PROPERTY_NAMES = new String[] {
		"Packets In",
		"Packets Out",
		"Bad Community Names",
		"Get Requests",
		"Set Requests",
		"Traps Sent"
	};
	
	public Variant7() {
		try {
			setLayout(new GridLayout());
			for (int i = 0; i < 3; ++i) {
				// Set up connection.
				SnmpTarget target = new SnmpTarget(HOSTS[i], PORT, COMMUNITY, COMMUNITY, 1);
				session = new SnmpSession(target);
				SnmpPoller poller = new SnmpPoller(session);
				JPanel pane = new JPanel();
				pane.setLayout(new GridLayout(PROPERTIES.length, 2));
				data.add(new HashMap<>());
				for (int j = 0; j < PROPERTIES.length; ++j) {
					JLabel label = new JLabel(PROPERTY_NAMES[j]);
					JLabel value = new JLabel("0");
					pane.add(label);
					pane.add(value);
					data.get(i).put(PROPERTIES[j], value);
				}
				final int index = i;
				poller.addListener((sender, msg) -> {
					if (msg.getType() != Msg.ERROR_TYPE) {
						SnmpPdu pdu = (SnmpPdu)msg;
						SnmpVarBind[] binds = pdu.getVarBinds();
						for (int j = 0; j < binds.length; ++j) {
							data.get(index).get(PROPERTIES[j]).setText(binds[j].getValue().toString());
						}
					}
				});
				getContentPane().add(pane);
				poller.snmpGetNextPoll(PROPERTIES, 10);
			}
			pack();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
