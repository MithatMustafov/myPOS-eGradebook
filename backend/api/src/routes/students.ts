import { FastifyInstance, FastifyRequest, FastifyReply } from 'fastify';
import pool from '../config/db';

export default async function studentRoutes(
  fastify: FastifyInstance,
  options: any
): Promise<void> {
  // Get all students
  fastify.get('/students', async (request: FastifyRequest, reply: FastifyReply) => {
    try {
      const result = await pool.query('SELECT * FROM students ORDER BY full_name');
      return { students: result.rows };
    } catch (error) {
      request.log.error(error);
      return reply.status(500).send({ error: 'Database query failed' });
    }
  });

  // Add a new student
  fastify.post('/students', async (request: FastifyRequest, reply: FastifyReply) => {
    const { full_name, date_of_birth } = request.body as any;
    try {
      const result = await pool.query(
        'INSERT INTO students (full_name, date_of_birth) VALUES ($1, $2) RETURNING *',
        [full_name, date_of_birth]
      );
      return result.rows[0];
    } catch (error) {
      request.log.error(error);
      return reply.status(500).send({ error: 'Failed to add student' });
    }
  });

  // Update a student
  fastify.put('/students/:id', async (request: FastifyRequest, reply: FastifyReply) => {
    const { id } = request.params as any;
    const { full_name, date_of_birth } = request.body as any;
    try {
      const result = await pool.query(
        'UPDATE students SET full_name = $1, date_of_birth = $2 WHERE id = $3 RETURNING *',
        [full_name, date_of_birth, id]
      );
      if (result.rows.length === 0) {
        return reply.status(404).send({ error: 'Student not found' });
      }
      return result.rows[0];
    } catch (error) {
      request.log.error(error);
      return reply.status(500).send({ error: 'Failed to update student' });
    }
  });

  // Delete a student
  fastify.delete('/students/:id', async (request: FastifyRequest, reply: FastifyReply) => {
    const { id } = request.params as any;
    try {
      const result = await pool.query('DELETE FROM students WHERE id = $1 RETURNING *', [id]);
      if (result.rows.length === 0) {
        return reply.status(404).send({ error: 'Student not found' });
      }
      return { message: 'Student deleted successfully' };
    } catch (error) {
      request.log.error(error);
      return reply.status(500).send({ error: 'Failed to delete student' });
    }
  });
}