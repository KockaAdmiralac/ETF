import bibliotekar from './routes/bibliotekar';
import citalac from './routes/citalac';
import {connect} from 'mongoose';
import cors from 'cors';
import express from 'express';
import login from './routes/login';

connect('mongodb://127.0.0.1:27017/biblioteka2022');

const app = express();
app.use(express.json());
app.use(cors());
app.use('/login', login);
app.use('/citalac', citalac);
app.use('/bibliotekar', bibliotekar);

app.listen(4000, () => console.info('Running on port 4000'));
