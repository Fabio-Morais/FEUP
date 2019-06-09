/*
1  Que candidatos concorreram às autárquicas de 'Lisboa'?
*/

SELECT id, nome 
FROM candidato
	JOIN autarquia USING(cod)
WHERE designacao='Lisboa'

/* ****** ******************************* ************************ *************** ***/

/*
2  Quantos candidatos do 'Partido da Direita' obtiveram mais de 1 voto?
*/
SELECT COUNT(*)
FROM candidato
	JOIN partido USING(sigla)
WHERE candidato.votos>1 AND partido.nome='Partido da Direita'

/* ****** ******************************* ************************ *************** ***/

/*
3  Qual é a média de idades dos candidatos de cada partido? Ordene a resposta do partido com maior média para o com menor. Em caso de empate, ordene pelo nome do partido alfabeticamente.
*/

SELECT partido.nome, AVG(candidato.idade) AS media
FROM candidato
	JOIN partido USING (sigla)
GROUP BY partido.nome
ORDER BY media DESC

/* ****** ******************************* ************************ *************** ***/

/*
4  Que partidos têm candidatos com uma média de idades superior a 45 anos?
*/

SELECT partido.nome
FROM partido 
	JOIN candidato USING(sigla)
GROUP BY partido.nome
HAVING AVG(candidato.idade)>45




/* ****** ******************************* ************************ *************** ***/

/*
5  Que autarquias não tiveram nenhum candidato do 'Partido do Meio'?
*/

SELECT cod, designacao
FROM (
  SELECT cod, designacao, SUM(case partido.nome WHEN 'Partido do Meio' THEN 1
						else 0 END) as aux
 FROM autarquia 
        LEFT JOIN candidato USING (cod)
        LEFT JOIN partido USING(sigla)
  GROUP BY designacao, cod) AS tab
WHERE aux=0

/*OU*/
SELECT cod,designacao
FROM autarquia
EXCEPT
SELECT cod,designacao
FROM  autarquia
	JOIN candidato USING (cod)
    LEFT JOIN partido USING(sigla)
WHERE partido.nome = 'Partido do Meio'
GROUP BY cod,designacao

/*OU*/
SELECT autarquia.cod, autarquia.designacao FROM

(SELECT candidato.cod, partido.nome FROM candidato 
INNER JOIN partido
ON candidato.sigla = partido.sigla
WHERE partido.nome = 'Partido do Meio') as s1

RIGHT JOIN autarquia
ON autarquia.cod = s1.cod
WHERE s1.cod IS NULL

/* ****** ******************************* ************************ *************** ***/


/*
6    Quantos eleitores se abstiveram em cada autarquia? 
*/

SELECT autarquia.designacao, 
CASE
	WHEN tab.quantidade is null THEN 0
    ELSE tab.quantidade
END AS quantidade
FROM autarquia
	LEFT JOIN (
	SELECT cod,designacao, COUNT(votou) as quantidade
	FROM autarquia
		JOIN eleitor USING(cod)
	GROUP BY designacao, votou, cod
	HAVING votou='false') AS tab USING(cod)

/*OU*/
SELECT autarquia.designacao,COALESCE(quantidade,0)
FROM autarquia
	LEFT JOIN (
	SELECT cod,designacao, COUNT(votou) as quantidade
	FROM autarquia
		JOIN eleitor USING(cod)
	GROUP BY designacao, votou, cod
	HAVING votou='false') AS tab USING(cod)

/* ****** ******************************* ************************ *************** ***/
/*
7     Que autarquias tiveram mais eleitores inscritos? 
*/
SELECT designacao
    FROM autarquia 
        JOIN eleitor USING (cod)
GROUP BY designacao
HAVING count(*)=(SELECT MAX(tab.co)
  FROM(
    SELECT designacao, count(*) as co
    FROM autarquia 
        JOIN eleitor USING (cod)
    GROUP BY designacao) AS tab)


/*OU*/
select designacao, case when count is null then 0
                    else count
                   end
from autarquia
left join (
	select cod, count(votou)
  	from eleitor
  	where votou='false'
  	group by cod
  	
) as t1
using (cod)
/* ****** ******************************* ************************ *************** ***/
/*
8    Qual o código das autarquias em que o 'PD' obteve maioria absoluta? 
*/

SELECT cod
FROM(
  SELECT SUM(votos) as soma, cod, aux.maxim
  FROM candidato
      LEFT JOIN (SELECT cod, MAX(votos) as maxim
                FROM candidato
                WHERE sigla='PD'
                GROUP BY cod, sigla
                ORDER BY maxim DESC
                ) AS aux USING(cod)
  WHERE sigla<>'PD'
  GROUP BY cod ,aux.maxim
) AS tab
WHERE maxim>soma 
ORDER BY maxim DESC
LIMIT 1


/*OU*/
select distinct cod
from
  candidato
join 
	(select cod, sum(votos) TOTAL
   from candidato
   group by cod
   order by cod) as total_vote
using (cod)
where votos> (total-votos)
	and sigla='PD'
order by cod
