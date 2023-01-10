import Book from '../models/Book';
import {Router} from 'express';

const router = Router();

router.get('/', async function(req, res) {
    const person = req.query.username;
    const query = person ? {person} : {};
    const books = await Book.find(query);
    res.json({books});
});

router.post('/', async function(req, res) {
    const {_id} = req.body;
    const person = req.body.username;
    const today = new Date();
    today.setDate(today.getDate() + 14);
    await Book.updateOne(
        {
            _id
        },
        {
            $set: {
                deadline: person ? today.toISOString() : null,
                person: person ?? null
            }
        }
    );
    res.json({success: true});
});

export default router;
