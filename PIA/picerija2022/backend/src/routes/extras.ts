import Extra from '../models/extra';
import {Router} from 'express';

const router = Router();

router.get('/', async function(_, res) {
    const extras = await Extra.find();
    res.json({extras});
});

router.patch('/', async function(req, res) {
    const {id} = req.body;
    await Extra.updateOne(
        {
            _id: id
        },
        {
            $inc: {
                amount: 5
            }
        }
    );
    res.json({message: 'OK'});
});

export default router;
