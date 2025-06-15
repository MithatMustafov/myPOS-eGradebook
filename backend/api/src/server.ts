import Fastify from 'fastify';
import pool from './config/db';
import studentRoutes from './routes/students';

const fastify = Fastify({
  logger: true,
});

fastify.register(studentRoutes);

const start = async () => {
  try {
    await fastify.listen({ port: 3000 });
    console.log('Server running at http://localhost:3000');
  } catch (err) {
    fastify.log.error(err);
    process.exit(1);
  }
};

start();