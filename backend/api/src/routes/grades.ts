import { FastifyInstance, FastifyRequest, FastifyReply } from 'fastify';
import pool from '../config/db';

export default async function gradeRoutes(
  fastify: FastifyInstance,
  options: any
): Promise<void> {
  // Get all grades
  fastify.get('/grades', async (request: FastifyRequest, reply: FastifyReply) => {
    try {
      const result = await pool.query(`
        SELECT g.*, s.full_name as student_name, sub.name as subject_name 
        FROM grades g
        JOIN students s ON g.student_id = s.id
        JOIN subjects sub ON g.subject_id = sub.id
      `);
      return { grades: result.rows };
    } catch (error) {
      request.log.error(error);
      return reply.status(500).send({ error: 'Database query failed' });
    }
  });

  // Add a new grade
  fastify.post('/grades', async (request: FastifyRequest, reply: FastifyReply) => {
    const { student_id, subject_id, grade, date } = request.body as any;
    
    // Validate grade range (2-6)
    if (grade < 2 || grade > 6) {
      return reply.status(400).send({ error: 'Grade must be between 2 and 6' });
    }

    try {
      const result = await pool.query(
        'INSERT INTO grades (student_id, subject_id, grade, date) VALUES ($1, $2, $3, $4) RETURNING *',
        [student_id, subject_id, grade, date]
      );
      return result.rows[0];
    } catch (error) {
      request.log.error(error);
      return reply.status(500).send({ error: 'Failed to add grade' });
    }
  });

  // Update a grade
  fastify.put('/grades/:id', async (request: FastifyRequest, reply: FastifyReply) => {
    const { id } = request.params as any;
    const { grade, date } = request.body as any;

    // Validate grade range (2-6)
    if (grade < 2 || grade > 6) {
      return reply.status(400).send({ error: 'Grade must be between 2 and 6' });
    }

    try {
      const result = await pool.query(
        'UPDATE grades SET grade = $1, date = $2 WHERE id = $3 RETURNING *',
        [grade, date, id]
      );
      if (result.rows.length === 0) {
        return reply.status(404).send({ error: 'Grade not found' });
      }
      return result.rows[0];
    } catch (error) {
      request.log.error(error);
      return reply.status(500).send({ error: 'Failed to update grade' });
    }
  });

  // Delete a grade
  fastify.delete('/grades/:id', async (request: FastifyRequest, reply: FastifyReply) => {
    const { id } = request.params as any;
    try {
      const result = await pool.query('DELETE FROM grades WHERE id = $1 RETURNING *', [id]);
      if (result.rows.length === 0) {
        return reply.status(404).send({ error: 'Grade not found' });
      }
      return { message: 'Grade deleted successfully' };
    } catch (error) {
      request.log.error(error);
      return reply.status(500).send({ error: 'Failed to delete grade' });
    }
  });
} 