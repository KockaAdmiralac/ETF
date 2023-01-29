import {Entity, ManyToOne, OneToMany, PrimaryGeneratedColumn} from 'typeorm';
import Message from './Message';
import User from './User';
import Workshop from './Workshop';

/**
 * Entity class for comments in the database.
 */
@Entity()
export default class Thread {
    @PrimaryGeneratedColumn()
    id!: number;
    @ManyToOne(() => User, user => user.threads, {
        eager: true,
        onDelete: 'CASCADE'
    })
    user!: User;
    @ManyToOne(() => Workshop, workshop => workshop.threads, {
        eager: true,
        onDelete: 'CASCADE'
    })
    workshop!: Workshop;
    @OneToMany(() => Message, message => message.thread, {
        eager: true
    })
    messages!: Message[];
}
