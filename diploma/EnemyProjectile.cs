using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyProjectile : MonoBehaviour
{
    public GameObject impactEffect;

    void OnCollisionEnter (Collision col)
    {
        if (col.gameObject.tag != "EnemyBullet" && col.gameObject.tag != "Enemy")
        {
            var impact = Instantiate(impactEffect, col.contacts[0].point, Quaternion.identity) as GameObject;

            FirstPersonController playerController = col.gameObject.GetComponent<FirstPersonController>();
            if (playerController != null)
            {
                playerController.TakeDamage(25f);
            }

            Destroy(impact, 2);
            Destroy(gameObject);
        }
    }
}
