import {
    Column,
    CreateDateColumn,
    Entity,
    ManyToOne,
    PrimaryGeneratedColumn
} from 'typeorm';
import Thread from './Thread';
import User from './User';

/**
 * Entity class for comments in the database.
 */
@Entity()
export default class Message {
    @PrimaryGeneratedColumn()
    id!: number;
    @Column()
    text!: string;
    @CreateDateColumn()
    date!: Date;
    @ManyToOne(() => User, {
        eager: true,
        onDelete: 'CASCADE'
    })
    user!: User;
    @ManyToOne(() => Thread, thread => thread.messages, {
        onDelete: 'CASCADE'
    })
    thread?: Thread;
}
