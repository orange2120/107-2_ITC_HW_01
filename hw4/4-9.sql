SELECT JobTitle, count(JobTitle) FROM JOB AS J
JOIN ASSIGNMENT AS A ON J.JobId = A.JobId
GROUP BY JobTitle
ORDER BY count(JobTitle) DESC
