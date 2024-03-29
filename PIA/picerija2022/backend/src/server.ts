import {connect} from 'mongoose';
import cors from 'cors';
import express from 'express';
import extras from './routes/extras';
import orders from './routes/orders';
import users from './routes/users';

connect('mongodb://localhost:27017/local');

const app = express();
app.use(express.json());
app.use(cors());
app.use('/users', users);
app.use('/orders', orders);
app.use('/extras', extras);

app.listen(4000, () => console.info('Running.'));
