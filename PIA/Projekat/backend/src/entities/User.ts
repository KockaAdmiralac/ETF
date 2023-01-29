import {
    Column,
    Entity,
    ManyToMany,
    OneToMany,
    PrimaryGeneratedColumn
} from 'typeorm';
import Comment from './Comment';
import Signup from './Signup';
import Thread from './Thread';
import Workshop from './Workshop';

export enum UserStatus {
    ACTIVE = 'active',
    INACTIVE = 'inactive',
    UNREVIEWED = 'unreviewed'
}

export enum UserRole {
    BASIC = 'basic',
    ORGANIZATION = 'organization',
    ADMIN = 'admin'
}

/**
 * Entity class for users in the database.
 */
@Entity()
export default class User {
    @PrimaryGeneratedColumn()
    id!: number;
    @Column({unique: true})
    username!: string;
    @Column()
    password!: string;
    @Column({unique: true})
    email!: string;
    @Column()
    name!: string;
    @Column()
    surname!: string;
    @Column()
    phone!: string;
    @Column({nullable: true})
    organization!: string;
    @Column({nullable: true})
    address!: string;
    @Column({nullable: true})
    oid!: number;
    @Column({
        default: UserRole.BASIC,
        enum: UserRole,
        type: 'enum'
    })
    role!: UserRole;
    @Column()
    hasAvatar!: boolean;
    @Column({
        default: UserStatus.UNREVIEWED,
        enum: UserStatus,
        type: 'enum'
    })
    status!: UserStatus;
    @OneToMany(() => Comment, comment => comment.user)
    comments?: Comment[];
    @OneToMany(() => Signup, signup => signup.user)
    signups?: Signup[];
    @OneToMany(() => Workshop, workshop => workshop.user)
    workshops?: Workshop[];
    @ManyToMany(() => Workshop, workshop => workshop.likedUsers, {
        onDelete: 'CASCADE'
    })
    likedWorkshops!: Workshop[];
    @Column({
        nullable: true,
        type: 'text'
    })
    passwordResetToken!: string | null;
    @Column({
        nullable: true,
        type: 'datetime'
    })
    passwordResetIssuedAt!: Date | null;
    @OneToMany(() => Thread, thread => thread.user)
    threads?: Thread[];
}
