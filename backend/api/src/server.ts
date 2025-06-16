import Fastify from 'fastify';
import studentRoutes from './routes/students';
import subjectRoutes from './routes/subjects';
import gradeRoutes from './routes/grades';
import analyticsRoutes from './routes/analytics';

const fastify = Fastify({
  logger: true,
});

// Register routes
fastify.register(studentRoutes);
fastify.register(subjectRoutes);
fastify.register(gradeRoutes);
fastify.register(analyticsRoutes);

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