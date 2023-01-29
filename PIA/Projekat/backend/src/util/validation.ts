import {ObjectOrTupleValidations, objectOf} from '@altostra/type-validations';
import {Response} from 'express';

/**
 * Middleware to validate request parameters.
 * @param validations Request validations to perform
 * @param body a
 * @param response Express server response to the user
 * @returns Whether the validation succeeded
 */
export function validateRequest<T extends object>(
    validations: ObjectOrTupleValidations<T>,
    body: any,
    response: Response
): body is T {
    const validator = objectOf<T>(validations);
    const result = validator(body);
    if (!result) {
        response.status(400).json({
            error: 'Invalid request body.'
        });
    }
    return result;
}
