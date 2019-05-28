SELECT J.JobTitle, count(J.JobTitle) FROM JOB AS J
JOIN ASSIGNMENT AS A ON J.JobId = A.JobId
GROUP BY J.JobTitle

HAVING count(J.JobTitle) >= (
SELECT  DISTINCT count(J.JobTitle) FROM JOB AS J
JOIN ASSIGNMENT AS A ON J.JobId = A.JobId
GROUP BY J.JobTitle
ORDER BY count(J.JobTitle) DESC
LIMIT 2,0) -- 2,0 represents 3rd largest number

ORDER BY count(J.JobTitle) DESC
