package rs.ac.bg.etf.rm2.projekat;

import java.awt.GridLayout;
import java.awt.TextArea;
import java.net.SocketException;
import java.time.LocalDateTime;

import com.ireasoning.protocol.snmp.SnmpConst;
import com.ireasoning.protocol.snmp.SnmpTrapdSession;
import com.ireasoning.protocol.snmp.SnmpV1Trap;

public class Variant6 extends Variant {
	private static final long serialVersionUID = -4615255637719562486L;
	private static final String BGP_OID = ".1.3.6.1.2.1.15.7";
	private TextArea textArea;
	
	public Variant6() {
		new Thread(() -> {
			SnmpTrapdSession session = null;
			try {
				session = new SnmpTrapdSession(LISTENER_PORT);
				session.addListener((sender, msg) -> {
					if (msg.getType() == SnmpConst.V1TRAP) {
						SnmpV1Trap trap = (SnmpV1Trap) msg;
						if (!trap.getCommunity().equals(COMMUNITY)) {
							return;
						}
						if (!trap.getEnterprise().toString().equals(BGP_OID)) {
							return;
						}
						String router = "unknown";
						String routerIp = trap.getIpAddress().toString();
						if (routerIp.equals("192.168.122.100")) {
							router = "R1";
						} else if (routerIp.equals("192.168.20.1")) {
							router = "R2";
						} else if (routerIp.equals("192.168.13.3")) {
							router = "R3";
						}
						LocalDateTime ldt = LocalDateTime.now();
						log("[" + ldt + "] Došlo je do događaja na ruteru " + router);
					}
				});
				session.waitForTrap();
			} catch (SocketException e) {
				e.printStackTrace();
			} finally {
				session.close();
			}
		}).start();
		setLayout(new GridLayout());
		textArea = new TextArea();
		textArea.setEditable(false);
		add(textArea);
		pack();
	}
	
	private void log(String text) {
		textArea.setText(textArea.getText() + text + "\n");
	}
}
