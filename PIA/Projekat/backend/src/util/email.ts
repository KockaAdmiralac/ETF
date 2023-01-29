import config from '../../config.json';
import {createTransport} from 'nodemailer';
import {readFile} from 'fs/promises';

const transport = createTransport({
    auth: {
        pass: config.emailPassword,
        user: config.emailUser
    },
    host: config.emailHost,
    port: config.emailPort,
    secure: config.emailPort === 465
});

/**
 * Replaces {placeholders} in the text of an email template.
 * @param template Email template contents
 * @param params Values to replace the placeholders with
 * @returns Template with placeholders replaced
 */
function replacePlaceholders(
    template: string,
    params: Record<string, string>
): string {
    return template.replaceAll(
        /\{([^}]+)\}/ug,
        (_, key) => params[key] || 'MISSING VALUE'
    );
}

/**
 * Sends an email using a specified template, to a specified email address.
 * @param template Name of the email to use
 * @param params Values to replace placeholders in the template with
 * @param to Email address to send the email to
 * @param subject Subject of the email
 */
export async function sendEmail(
    template: string,
    params: Record<string, string>,
    to: string,
    subject: string
) {
    const templateContentsText = await readFile(`templates/${template}.tmpl.txt`, {
        encoding: 'utf-8'
    });
    const templateContentsHtml = await readFile(`templates/${template}.tmpl.html`, {
        encoding: 'utf-8'
    });
    const text = replacePlaceholders(templateContentsText, params);
    const html = replacePlaceholders(templateContentsHtml, params);
    await transport.sendMail({
        from: 'PIA projekat <si@kocka.tech>',
        html,
        subject,
        text,
        to
    });
}
