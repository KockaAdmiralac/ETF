import {Router} from 'express';
import User from '../models/User';

const router = Router();

router.post('/', async function(req, res) {
    const {username, password, type} = req.body;
    const user = await User.findOne({
        password,
        type,
        username
    });
    if (user) {
        res.json({user});
    } else {
        res.status(400).json({
            error: 'No user with given credentials found.'
        });
    }
});

export default router;
