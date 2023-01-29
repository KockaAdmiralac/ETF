import {Entity, ManyToOne, PrimaryGeneratedColumn} from 'typeorm';
import Workshop from './Workshop';

/**
 * Entity class for photos in the database.
 */
@Entity()
export default class Photo {
    @PrimaryGeneratedColumn()
    id!: number;
    @ManyToOne(() => Workshop, workshop => workshop.photos, {
        onDelete: 'CASCADE'
    })
    workshop?: Workshop;
}
