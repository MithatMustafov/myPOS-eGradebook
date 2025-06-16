import { FastifyInstance, FastifyRequest, FastifyReply } from 'fastify';
import pool from '../config/db';

export default async function analyticsRoutes(
  fastify: FastifyInstance,
  options: any
): Promise<void> {
  // Get average grade in a specific subject for a student
  fastify.get('/analytics/average/:studentId/:subjectId', async (request: FastifyRequest, reply: FastifyReply) => {
    const { studentId, subjectId } = request.params as any;
    try {
      const result = await pool.query(
        'SELECT AVG(grade)::numeric(10,2) as average FROM grades WHERE student_id = $1 AND subject_id = $2',
        [studentId, subjectId]
      );
      return result.rows[0].average || 0;
    } catch (error) {
      request.log.error(error);
      return reply.status(500).send({ error: 'Failed to calculate average' });
    }
  });

  // Get overall average grade for a student
  fastify.get('/analytics/average/:studentId', async (request: FastifyRequest, reply: FastifyReply) => {
    const { studentId } = request.params as any;
    try {
      const result = await pool.query(
        'SELECT AVG(grade)::numeric(10,2) as average FROM grades WHERE student_id = $1',
        [studentId]
      );
      return result.rows[0].average || 0;
    } catch (error) {
      request.log.error(error);
      return reply.status(500).send({ error: 'Failed to calculate overall average' });
    }
  });

  // Get top students (average > 5.50)
  fastify.get('/analytics/top-students', async (request: FastifyRequest, reply: FastifyReply) => {
    try {
      const result = await pool.query(`
        SELECT 
          s.id,
          s.full_name,
          AVG(g.grade)::numeric(10,2) as average_grade
        FROM students s
        JOIN grades g ON s.id = g.student_id
        GROUP BY s.id, s.full_name
        HAVING AVG(g.grade) > 5.50
        ORDER BY average_grade DESC
      `);
      return result.rows;
    } catch (error) {
      request.log.error(error);
      return reply.status(500).send({ error: 'Failed to fetch top students' });
    }
  });

  // Get students who need remedial exam (grade = 2)
  fastify.get('/analytics/remedial-exam', async (request: FastifyRequest, reply: FastifyReply) => {
    try {
      const result = await pool.query(`
        SELECT DISTINCT
          s.id,
          s.full_name,
          sub.name as subject_name
        FROM students s
        JOIN grades g ON s.id = g.student_id
        JOIN subjects sub ON g.subject_id = sub.id
        WHERE g.grade = 2
        ORDER BY s.full_name, sub.name
      `);
      return result.rows;
    } catch (error) {
      request.log.error(error);
      return reply.status(500).send({ error: 'Failed to fetch remedial exam students' });
    }
  });

  // Get students with low grades (average < 3.00)
  fastify.get('/analytics/low-grades', async (request: FastifyRequest, reply: FastifyReply) => {
    try {
      const result = await pool.query(`
        SELECT 
          s.id,
          s.full_name,
          AVG(g.grade)::numeric(10,2) as average_grade
        FROM students s
        JOIN grades g ON s.id = g.student_id
        GROUP BY s.id, s.full_name
        HAVING AVG(g.grade) < 3.00
        ORDER BY average_grade ASC
      `);
      return result.rows;
    } catch (error) {
      request.log.error(error);
      return reply.status(500).send({ error: 'Failed to fetch students with low grades' });
    }
  });

  // Get students with birthdays today
  fastify.get('/analytics/birthdays-today', async (request: FastifyRequest, reply: FastifyReply) => {
    try {
      const result = await pool.query(`
        SELECT id, full_name, date_of_birth
        FROM students
        WHERE 
          EXTRACT(MONTH FROM date_of_birth) = EXTRACT(MONTH FROM CURRENT_DATE)
          AND EXTRACT(DAY FROM date_of_birth) = EXTRACT(DAY FROM CURRENT_DATE)
        ORDER BY full_name
      `);
      return result.rows;
    } catch (error) {
      request.log.error(error);
      return reply.status(500).send({ error: 'Failed to fetch birthday students' });
    }
  });
} 