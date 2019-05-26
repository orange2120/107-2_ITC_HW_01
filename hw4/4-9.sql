SELECT JobTitle, count(JobTitle) FROM JOB
GROUP BY JobTitle
ORDER BY count(JobTitle) DESC
