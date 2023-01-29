import express, {json, urlencoded} from 'express';
import config from '../config.json';
import controllers from './controllers';
import cors from 'cors';
import {initDatabase} from './util/database';

/**
 * Asynchronous entry point.
 */
async function main() {
    await initDatabase();
    const app = express();
    app.use(json());
    app.use(urlencoded({extended: false}));
    app.use(cors({
        credentials: true,
        origin: config.frontendUrl
    }));
    app.use('/', express.static('public'));
    for (const [route, router] of Object.entries(controllers)) {
        app.use(`/${route}`, router);
    }
    app.listen(config.port, () => console.info('Running!'));
}

main();
