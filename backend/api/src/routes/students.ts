import { FastifyInstance, FastifyRequest, FastifyReply } from 'fastify';
import pool from '@/config/db';

export default async function studentRoutes(
  fastify: FastifyInstance,
  options: any
): Promise<void> {
  fastify.get('/students', async (request: FastifyRequest, reply: FastifyReply) => {
    try {
      const result = await pool.query('SELECT * FROM students');
      return { students: result.rows };
    } catch (error) {
      request.log.error(error);
      return reply.status(500).send({ error: 'Database query failed' });
    }
  });
}