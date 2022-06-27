class CarAgency {
    public static final STANDARD_VEHICLE = 0;
    public static final LUXURY_VEHICLE = 1;
    public static final ANY_VEHICLE = 2;
    private int standardVehicles = 100;
    private int luxuryVehicles = 10;
    private final Condition[] queues = new Condition[3];
    private int ticket = 1;
    public CarAgency() {
        for (int i = 0; i < 3; ++i) {
            queues[i] = new Condition();
        }
    }
    public synchronized void rentCar(int which) {
        int myTicket = ticket++;
        if (
            standardVehicles == 0 && which == STANDARD_VEHICLE ||
            luxuryVehicles == 0 && which == LUXURY_VEHICLE ||
            (standardVehicles == 0 && luxuryVehicles == 0)
        ) {
            // Нема возила, чекамо
            queues[which].wait(myTicket);
            // Број возила је смањен већ при сигнализирању
        } else if (which == STANDARD_VEHICLE) {
            // Желели смо стандардно возило и добили смо
            --standardVehicles;
        } else if (which == LUXURY_VEHICLE) {
            // Желели смо луксузно возило и добили смо
            --luxuryVehicles;
        } else if (standardVehicles == 0) {
            // Желели смо било које возило и добили смо луксузно
            --luxuryVehicles;
        } else {
            // Желели смо било које возило и добили смо стандардно
            --standardVehicles;
        }
    }
    public synchronized void returnCar(int which) {
        if (which == STANDARD_VEHICLE) {
            ++standardVehicles;
            boolean qStandardVehicle = queues[STANDARD_VEHICLE].queue();
            boolean qAnyVehicle = queues[ANY_VEHICLE].queue();
            if (qStandardVehicle || qAnyVehicle) {
                --standardVehicles;
            }
            if (qStandardVehicle && qAnyVehicle) {
                if (queues[STANDARD_VEHICLE].minrank() < queues[ANY_VEHICLE].minrank()) {
                    queues[STANDARD_VEHICLE].signal();
                } else {
                    queues[ANY_VEHICLE].signal();
                }
            } else if (qStandardVehicle) {
                queues[STANDARD_VEHICLE].signal();
            } else if (qAnyVehicle) {
                queues[ANY_VEHICLE].signal();
            }
        } else {
            ++luxuryVehicles;
            boolean qLuxuryVehicle = queues[LUXURY_VEHICLE].queue();
            boolean qAnyVehicle = queues[ANY_VEHICLE].queue();
            if (qLuxuryVehicle || qAnyVehicle) {
                --luxuryVehicles;
            }
            if (qLuxuryVehicle && qAnyVehicle) {
                if (queues[LUXURY_VEHICLE].minrank() < queues[ANY_VEHICLE].minrank()) {
                    queues[LUXURY_VEHICLE].signal();
                } else {
                    queues[ANY_VEHICLE].signal();
                }
            } else if (qLuxuryVehicle) {
                queues[LUXURY_VEHICLE].signal();
            } else if (qAnyVehicle) {
                queues[ANY_VEHICLE].signal();
            }
        }
    }
}
