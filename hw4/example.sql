SELECT * FROM EMPLOYEE;
-- 4-0
SELECT JobTitle, StartDate, TermDate 
FROM JOB JOIN ASSIGNMENT 
ON JOB.JobId=ASSIGNMENT.JobId JOIN EMPLOYEE ON ASSIGNMENT.EmpId=EMPLOYEE .EmpId WHERE EMPLOYEE.Name='Ethan';