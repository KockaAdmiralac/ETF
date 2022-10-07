import {Router} from 'express';
import User from '../models/user';

const router = Router();

router.post('/login', async function(req, res) {
    const {password, username, type} = req.body;
    const user = await User.findOne({
        password,
        type,
        username
    });
    if (!user) {
        res.status(400).json({
            message: 'Invalid username, password or type.'
        });
        return;
    }
    res.json({
        // eslint-disable-next-line camelcase
        firstName: user.first_name,
        // eslint-disable-next-line camelcase
        lastName: user.last_name,
        message: 'OK'
    });
});

export default router;
