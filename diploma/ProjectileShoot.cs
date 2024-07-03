using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ProjectileShoot : MonoBehaviour
{
    public GameObject impactEffect;

    void OnCollisionEnter (Collision col)
    {
        if (col.gameObject.tag != "Bullet" && col.gameObject.tag != "Player")
        {
            var impact = Instantiate(impactEffect, col.contacts[0].point, Quaternion.identity) as GameObject;
            Destroy(impact, 2);

            EnemyAI enemyController = col.gameObject.GetComponent<EnemyAI>();
            if (enemyController != null)
            {
                enemyController.TakeDamage();
            }
            Destroy(gameObject);
        }
    }
}
