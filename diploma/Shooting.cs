using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Shooting : MonoBehaviour
{
    public Camera cam;
    public GameObject projectile;
    public Transform firepoint;
    public float projectileSpeed = 30f;
    public float firerate = 4;

    public float maxCharge = 100f;
    public float currentCharge;
    public float shootChargeCost = 10f;
    public float passiveRegenRate = 4f;
    public float idleRegenRate = 10f;
    public float idleTime = 3f;
    public Slider chargeSlider;

    private Vector3 destination;
    private float timeToFire;
    private float lastShootTime;
    // Start is called before the first frame update
    void Start()
    {
        currentCharge = maxCharge;
        chargeSlider.maxValue = maxCharge;
        chargeSlider.value = currentCharge;
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetButton("Fire1") && Time.time >= timeToFire && currentCharge >= shootChargeCost)
        {
            timeToFire = Time.time + 1 / firerate;
            ShootProjectile();
            currentCharge -= shootChargeCost;
            lastShootTime = Time.time;
        }

        if (Time.time - lastShootTime >= idleTime)
        {
            currentCharge = Mathf.Min(currentCharge + idleRegenRate * Time.deltaTime, maxCharge);
        }
        else
        {
            currentCharge = Mathf.Min(currentCharge + passiveRegenRate * Time.deltaTime, maxCharge);
        }

        chargeSlider.value = Mathf.Lerp(chargeSlider.value, currentCharge, Time.deltaTime * 10f); 
    }

    void ShootProjectile()
    {
        Ray ray = cam.ViewportPointToRay(new Vector3(0.5f, 0.5f, 0));
        RaycastHit hit;

        if (Physics.Raycast(ray, out hit))
        {
            destination = hit.point;
        }
        else
            destination = ray.GetPoint(1000);

        InstantiateProjectile(firepoint);
    }

    void InstantiateProjectile(Transform firepoint)
    {
        var projectileObj = Instantiate(projectile, firepoint.position, Quaternion.identity) as GameObject;
        projectileObj.GetComponent<Rigidbody>().velocity = (destination - firepoint.position).normalized * projectileSpeed;
    }
}
