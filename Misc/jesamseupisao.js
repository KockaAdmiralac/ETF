'use strict';

const got = require('got');
const { CookieJar } = require('tough-cookie');
const { WebhookClient } = require('discord.js');
const config = require('./config.json');
const fs = require('fs');

const http = got.extend({
    cookieJar: new CookieJar(),
    prefixUrl: 'https://student.etf.bg.ac.rs/',
    resolveBodyOnly: true
}), webhook = new WebhookClient(config.id, config.token);

let viewState;

function getViewState(text) {
    return /<input type="hidden" name="javax.faces.ViewState" value="j_id(\d+)" \/>/.exec(text)[1];
}

async function interval() {
    const upis = await http('student/viewStudentUpis.jsf', {
        form: {
            menu: 'menu',
            'javax.faces.ViewState': `j_id${viewState}`,
            'menu:_idcl': 'menu_nav1_item20'
        },
        method: 'POST'
    });
    viewState = getViewState(upis);
    if (upis.includes('друга')) {
        console.log('Upisao si se');
        await webhook.send(`<@${config.userid}> Upisao si se`);
        process.exit();
    } else if (!upis.includes('2019/20')) {
        console.log('Nešto se sjebalo');
    } else {
        console.log('Nisi se upisao');
    }
}

function login() {
    return http('j_spring_security_check', {
        form: {
            j_username: config.username,
            j_password: config.password
        },
        method: 'POST'
    });
}

async function main() {
    viewState = getViewState(await login());
    setInterval(interval, 10000);
}

main();
