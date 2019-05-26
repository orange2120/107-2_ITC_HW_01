SELECT JobTitle, count(JobTitle),
RANK() OVER (
PARTITION BY JobTitle
ORDER BY CJ DESC
) CJRank
 FROM JOB
GROUP BY JobTitle
ORDER BY count(JobTitle)
