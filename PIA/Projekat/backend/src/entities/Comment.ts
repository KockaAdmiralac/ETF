import {
    Column,
    CreateDateColumn,
    Entity,
    ManyToOne,
    PrimaryGeneratedColumn
} from 'typeorm';
import User from './User';
import Workshop from './Workshop';

/**
 * Entity class for comments in the database.
 */
@Entity()
export default class Comment {
    @PrimaryGeneratedColumn()
    id!: number;
    @Column()
    text!: string;
    @CreateDateColumn()
    date!: Date;
    @ManyToOne(() => User, user => user.comments, {
        eager: true,
        onDelete: 'CASCADE'
    })
    user!: User;
    @ManyToOne(() => Workshop, workshop => workshop.comments, {
        onDelete: 'CASCADE'
    })
    workshop?: Workshop;
}
