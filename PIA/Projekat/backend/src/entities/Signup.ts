import {Column, Entity, ManyToOne, PrimaryGeneratedColumn} from 'typeorm';
import User from './User';
import Workshop from './Workshop';

export enum SignupStatus {
    PARTICIPATING = 'participating',
    REQUESTED = 'requested',
    QUEUED = 'queued'
}

/**
 * Entity class for signups in the database.
 */
@Entity()
export default class Signup {
    @PrimaryGeneratedColumn()
    id!: number;
    @Column({
        default: SignupStatus.REQUESTED,
        enum: SignupStatus,
        type: 'enum'
    })
    status!: SignupStatus;
    @ManyToOne(() => User, user => user.signups, {
        onDelete: 'CASCADE'
    })
    user!: User;
    @ManyToOne(() => Workshop, workshop => workshop.signups, {
        onDelete: 'CASCADE'
    })
    workshop!: Workshop;
}
