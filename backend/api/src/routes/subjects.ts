import { FastifyInstance, FastifyRequest, FastifyReply } from 'fastify';
import pool from '../config/db';

export default async function subjectRoutes(
  fastify: FastifyInstance,
  options: any
): Promise<void> {
  // Get all subjects
  fastify.get('/subjects', async (request: FastifyRequest, reply: FastifyReply) => {
    try {
      const result = await pool.query('SELECT * FROM subjects');
      return { subjects: result.rows };
    } catch (error) {
      request.log.error(error);
      return reply.status(500).send({ error: 'Database query failed' });
    }
  });

  // Add a new subject
  fastify.post('/subjects', async (request: FastifyRequest, reply: FastifyReply) => {
    const { name, teacher_name, room_number } = request.body as any;
    try {
      const result = await pool.query(
        'INSERT INTO subjects (name, teacher_name, room_number) VALUES ($1, $2, $3) RETURNING *',
        [name, teacher_name, room_number]
      );
      return result.rows[0];
    } catch (error) {
      request.log.error(error);
      return reply.status(500).send({ error: 'Failed to add subject' });
    }
  });

  // Update a subject
  fastify.put('/subjects/:id', async (request: FastifyRequest, reply: FastifyReply) => {
    const { id } = request.params as any;
    const { name, teacher_name, room_number } = request.body as any;
    try {
      const result = await pool.query(
        'UPDATE subjects SET name = $1, teacher_name = $2, room_number = $3 WHERE id = $4 RETURNING *',
        [name, teacher_name, room_number, id]
      );
      if (result.rows.length === 0) {
        return reply.status(404).send({ error: 'Subject not found' });
      }
      return result.rows[0];
    } catch (error) {
      request.log.error(error);
      return reply.status(500).send({ error: 'Failed to update subject' });
    }
  });

  // Delete a subject
  fastify.delete('/subjects/:id', async (request: FastifyRequest, reply: FastifyReply) => {
    const { id } = request.params as any;
    try {
      const result = await pool.query('DELETE FROM subjects WHERE id = $1 RETURNING *', [id]);
      if (result.rows.length === 0) {
        return reply.status(404).send({ error: 'Subject not found' });
      }
      return { message: 'Subject deleted successfully' };
    } catch (error) {
      request.log.error(error);
      return reply.status(500).send({ error: 'Failed to delete subject' });
    }
  });
} 