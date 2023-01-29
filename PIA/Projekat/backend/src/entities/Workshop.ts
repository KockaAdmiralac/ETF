import {
    Column,
    Entity,
    JoinTable,
    ManyToMany,
    ManyToOne,
    OneToMany,
    PrimaryGeneratedColumn
} from 'typeorm';
import Comment from './Comment';
import Photo from './Photo';
import Signup from './Signup';
import Thread from './Thread';
import User from './User';

/**
 * Entity class for workshops in the database.
 */
@Entity()
export default class Workshop {
    @PrimaryGeneratedColumn()
    id!: number;
    @Column()
    name!: string;
    @Column()
    date!: Date;
    @Column()
    place!: string;
    @Column({
        precision: 30,
        scale: 27,
        type: 'decimal'
    })
    latitude!: number;
    @Column({
        precision: 30,
        scale: 27,
        type: 'decimal'
    })
    longitude!: number;
    @Column()
    capacity!: number;
    @Column()
    description!: string;
    @Column()
    snippet!: string;
    @Column()
    active!: boolean;
    @ManyToOne(() => User, user => user.workshops, {
        eager: true,
        onDelete: 'CASCADE'
    })
    user!: User;
    @OneToMany(() => Photo, photo => photo.workshop, {
        eager: true
    })
    photos!: Photo[];
    @OneToMany(() => Signup, signup => signup.workshop)
    signups?: Signup[];
    @OneToMany(() => Comment, comment => comment.workshop, {
        eager: true
    })
    comments!: Comment[];
    @ManyToMany(() => User, user => user.likedWorkshops, {
        eager: true,
        onDelete: 'CASCADE'
    })
    @JoinTable()
    likedUsers!: User[];
    @OneToMany(() => Thread, thread => thread.workshop)
    threads?: Thread[];
}
