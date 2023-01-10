import Book from '../models/Book';
import {Router} from 'express';

const router = Router();

router.post('/', async function(req, res) {
    const book = new Book();
    const {id, title, author} = req.body;
    book.id = id;
    book.title = title;
    book.author = author;
    book.person = null;
    book.deadline = null;
    await book.save();
    res.json({success: true});
});

export default router;
