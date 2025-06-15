import { Pool } from 'pg';

const pool = new Pool({
    host: 'localhost',
    port: 5433,
    database: 'eGradebookDB',
    user: 'Username',
    password: 'Password',
});

export default pool;
