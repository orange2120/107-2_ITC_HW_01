SELECT COUNT(A.JobId) FROM ASSIGNMENT AS A
INNER JOIN JOB AS J ON J.JobId=A.JobId
WHERE J.JobTitle LIKE '%Manager%'