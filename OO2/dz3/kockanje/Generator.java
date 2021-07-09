package kockanje;

import java.util.Random;

public class Generator {
	private Random random = new Random();
	int broj(int donja, int gornja) {
		return random.nextInt(gornja - donja + 1) + donja;
	}
}
