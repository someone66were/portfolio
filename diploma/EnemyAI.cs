using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class EnemyAI : MonoBehaviour
{
    public float moveSpeed = 5f;
    public float detectionRange = 10f;
    public float shootingRange = 8f;
    public float fireRate = 4f;
    public GameObject projectilePrefab;
    public Transform firePoint;
    public float projectileSpeed = 5f;
    public Camera enemyCam;
    public LayerMask obstaclesLayer;
    public float hitsToKill = 3f;
    public float normalSpeed = 2f;
    public float speedWhileShooting = 0.5f;

    private Transform player;
    private float nextFireTime;
    private Vector3 destination;
    private Vector3 lastKnownPosition;
    private bool playerInSight;
    private NavMeshAgent navAgent;
    private float health;

    void Start()
    {
        player = GameObject.FindGameObjectWithTag("Player").transform;
        navAgent = GetComponent<NavMeshAgent>();
        navAgent.speed = normalSpeed;
        health = hitsToKill;
    }

    void Update()
    {
        if (player == null)
            return;

        float distanceToPlayer = Vector3.Distance(transform.position, player.position);
        playerInSight = IsPlayerInLineOfSight();

        if (distanceToPlayer <= detectionRange && playerInSight)
        {
            lastKnownPosition = player.position;
            navAgent.SetDestination(lastKnownPosition);

            if (distanceToPlayer <= shootingRange)
            {
                if (Time.time >= nextFireTime)
                {
                    Shoot();
                    nextFireTime = Time.time + 1f / fireRate;
                }
                // Замедление врага при стрельбе
                navAgent.speed = speedWhileShooting;
            }
            else
            {
                // Восстановление нормальной скорости
                navAgent.speed = normalSpeed;
            }
        }
        else if (lastKnownPosition != Vector3.zero)
        {
            navAgent.SetDestination(lastKnownPosition);

            // Сбросить последнюю известную позицию, если враг достиг её
            if (Vector3.Distance(transform.position, lastKnownPosition) < 0.1f)
            {
                lastKnownPosition = Vector3.zero;
            }

            // Восстановление нормальной скорости
            navAgent.speed = normalSpeed;
        }

        // Обновляем ориентацию firePoint
        UpdateFirePoint();
    }

    bool IsPlayerInLineOfSight()
    {
        Vector3 directionToPlayer = (player.position - transform.position).normalized;
        float distanceToPlayer = Vector3.Distance(transform.position, player.position);

        // Выполняем Raycast для проверки наличия препятствий
        if (!Physics.Raycast(transform.position, directionToPlayer, distanceToPlayer, obstaclesLayer))
        {
            return true;
        }
        return false;
    }

    void Shoot()
    {
        if (firePoint != null && projectilePrefab != null)
        {
            // Используем позицию игрока как точку назначения
            destination = player.position;

            // Поворот firePoint к игроку
            firePoint.LookAt(destination);

            InstantiateProjectile(firePoint);
        }
    }

    void InstantiateProjectile(Transform firePoint)
    {
        var projectileObj = Instantiate(projectilePrefab, firePoint.position, firePoint.rotation) as GameObject;
        projectileObj.GetComponent<Rigidbody>().velocity = (destination - firePoint.position).normalized * projectileSpeed;
    }

    void UpdateFirePoint()
    {
        if (firePoint != null && player != null)
        {
            firePoint.LookAt(player.position);
        }
    }

    public void TakeDamage()
    {
        health -= 1;
        if (health == 0)
        {
            Destroy(this.gameObject);
        }
    }
}