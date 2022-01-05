package rs.ac.bg.etf.is1.projekat.commands;

public class GetBackupCommand extends Command {
    private final boolean onlyS3;
    public GetBackupCommand() {
        this.onlyS3 = false;
    }
    public GetBackupCommand(boolean onlyS3) {
        this.onlyS3 = onlyS3;
    }
    @Override
    public Destination getDestination() {
        if (onlyS3) {
            return Destination.S3;
        }
        return Destination.ALL;
    }
    @Override
    public Command.Type getType() {
        return Command.Type.GET_BACKUP;
    }
}
