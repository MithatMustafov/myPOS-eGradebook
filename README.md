# myPOS-eGradebook

<div align="center">
  <h3>A Modern E-Gradebook System</h3>
</div>

## 📋 Overview

myPOS-eGradebook is a comprehensive electronic gradebook system designed to help educational institutions manage student grades, subjects, and academic analytics efficiently. The system consists of a desktop application built in C++ and a robust backend API.

## 💻 Technology Stack

### Frontend Desktop Application
- **Language:** C++
- **Build System:** Custom build scripts (build.bat, setup.bat)
- **UI Components:** Custom ASCII UI elements
- **Core Modules:**
  - Student Actions
  - Subject Actions
  - Grade Actions
  - Analytics Actions
  - Menu System

### Backend
- **API Framework:** Fastify (TypeScript)
- **Database:** PostgreSQL (Containerized)
- **Container Platform:** Docker
- **Key Features:**
  - Type-safe API with TypeScript
  - Modular Route Structure
  - PostgreSQL Pool Connection
  - Error Logging
  - Input Validation

## 🚀 Features

- **Student Management**
  - Add, edit, and manage student profiles
  - Track student performance
  - View individual student history

- **Subject Management**
  - Create and organize academic subjects
  - Assign teachers to subjects
  - Manage course materials

- **Grade Management**
  - Record and update student grades
  - Calculate grade averages
  - Generate grade reports

- **Analytics**
  - View detailed academic performance analytics
  - Generate statistical reports
  - Track progress over time

## 🏗️ Project Structure

```
myPOS-eGradebook/
├── frontend/
│   └── appDesktop/        # Desktop application (C++)
│       ├── src/           # Source code
│       ├── build/         # Build outputs
│       └── build.bat      # Build script
│
└── backend/
    ├── api/              # Backend API
    └── database/         # Database configurations and migrations
```

## 📋 Prerequisites

- C++ Compiler (for desktop application)
- Windows Operating System
- Docker Desktop
- Node.js (v14 or higher)
- npm (Node Package Manager)

## 🛠️ Installation & Setup

### 1. Database Setup (Docker)

1. Start Docker Desktop
2. Navigate to the database directory:
   ```bash
   cd backend/database
   ```
3. Start the PostgreSQL container:
   ```bash
   docker-compose up -d
   ```
4. Verify the database is running:
   ```bash
   docker ps
   ```

### 2. Backend API Setup

1. Navigate to the API directory:
   ```bash
   cd backend/api
   ```

2. Install dependencies:
   ```bash
   npm install
   ```

3. Run database migrations:
   ```bash
   npm run migrate
   ```

4. Start the API server:
   ```bash
   # Development mode
   npm run dev

   # Production mode
   npm start
   ```

   The API will be available at `http://localhost:3000`

### 3. Desktop Application Setup

1. Navigate to the desktop application directory:
   ```bash
   cd frontend/appDesktop
   ```

2. Run the setup script:
   ```bash
   setup.bat
   ```

3. Build the application:
   ```bash
   build.bat
   ```

4. The compiled application will be available in the `build` directory

## 🔌 API Endpoints

The API runs on `http://localhost:3000` by default. Here are all available endpoints:

### 👨‍🎓 Students (`/students`)
- `GET /students` - Get all students ordered by name
- `POST /students` - Add a new student
  - Body: `{ full_name, date_of_birth }`
- `PUT /students/:id` - Update a student
  - Body: `{ full_name, date_of_birth }`
- `DELETE /students/:id` - Delete a student

### 📚 Subjects (`/subjects`)
- `GET /subjects` - Get all subjects
- `POST /subjects` - Add a new subject
  - Body: `{ name, teacher_name, room_number }`
- `PUT /subjects/:id` - Update a subject
  - Body: `{ name, teacher_name, room_number }`
- `DELETE /subjects/:id` - Delete a subject

### 📝 Grades (`/grades`)
- `GET /grades` - Get all grades with student and subject details
- `POST /grades` - Add a new grade
  - Body: `{ student_id, subject_id, grade, date }`
  - Note: Grade must be between 2 and 6
- `PUT /grades/:id` - Update a grade
  - Body: `{ grade, date }`
  - Note: Grade must be between 2 and 6
- `DELETE /grades/:id` - Delete a grade

### 📊 Analytics (`/analytics`)
- `GET /analytics/average/:studentId/:subjectId` - Get student's average grade in a specific subject
- `GET /analytics/average/:studentId` - Get student's overall average grade
- `GET /analytics/top-students` - Get top students (average > 5.50)
- `GET /analytics/remedial-exam` - Get students who need remedial exam (grade = 2)
- `GET /analytics/low-grades` - Get students with low grades (average < 3.00)
- `GET /analytics/birthdays-today` - Get students with birthdays today

### Database
- Default port: 5432
- Database name: mypos_gradebook
