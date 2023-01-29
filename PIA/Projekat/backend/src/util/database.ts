import {DataSource} from 'typeorm';
import config from '../../config.json';

const {username, password, database} = config;
export const Database = new DataSource({
    database,
    entities: ['src/entities/**/*.ts'],
    host: 'localhost',
    logging: false,
    password,
    synchronize: true,
    type: 'mysql',
    username
});

/**
 * Initializes the database connection.
 * @returns Initialized database connection
 */
export function initDatabase(): Promise<DataSource> {
    return Database.initialize();
}
