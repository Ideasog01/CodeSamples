using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

public class SpawnManager : MonoBehaviour
{
    public static int activeHostiles;

    [Header("Spawn Settings")]

    public Transform[] spawnArray;

    public Animator[] doorAnimators;

    [Header("Other")]

    [SerializeField]
    private Transform[] enemyPrefabs;

    [SerializeField]
    private Transform projectileParent;

    [SerializeField]
    private Transform enemyParent;

    [SerializeField]
    private bool activateGameMode;

    public List<EnemyEntity> enemyList = new List<EnemyEntity>();

    private List<PlayerProjectileController> _activePlayerProjectiles = new List<PlayerProjectileController>();

    private List<ProjectileController> _activeProjectiles = new List<ProjectileController>();

    private List<ProjectileController> _activeTurretProjectiles = new List<ProjectileController>();

    private List<ProjectileController> _seekerProjectiles = new List<ProjectileController>();

    private void Start()
    {
        activeHostiles = 0;

        if(activateGameMode)
        {
            SpawnWaveManager();
        }
    }

    public void SpawnWaveManager()
    {
        GameManager.waveManager = Instantiate(GameManager.gameSettings.SpawnPrefab.GetComponent<WaveManager>(), Vector3.zero, Quaternion.identity); //Spawn the WaveManager dependent on the selected game settings (difficulty level)
    }

    public PlayerProjectileController SpawnPlayerProjectile(Transform prefab, Vector3 position, Quaternion rotation)
    {
        PlayerProjectileController projectileToUse = null;

        foreach (PlayerProjectileController projectile in _activePlayerProjectiles) //Reuse projectile (avoids uneccessary use of memory)
        {
            if (!projectile.gameObject.activeSelf)
            {
                projectile.gameObject.SetActive(true);
                projectileToUse = projectile;
                break;
            }
        }

        if (projectileToUse == null) //Projectile not found, create a new one
        {
            projectileToUse = Instantiate(prefab.GetComponent<PlayerProjectileController>(), position, rotation);
            projectileToUse.transform.parent = projectileParent;
            _activePlayerProjectiles.Add(projectileToUse);
        }

        projectileToUse.InitialiseProjectile(position, rotation); //Reset the projectile

        return projectileToUse;
    }

    public void SpawnProjectile(Transform prefab, Vector3 position, Quaternion rotation)
    {
        ProjectileController projectileToUse = null;

        foreach (ProjectileController projectile in _activeProjectiles) //Reuse projectile (avoids uneccessary use of memory)
        {
            if(!projectile.gameObject.activeSelf)
            {
                projectile.gameObject.SetActive(true);
                projectileToUse = projectile;
                break;
            }
        }

        if(projectileToUse == null) //Projectile not found, create a new one
        {
            projectileToUse = Instantiate(prefab.GetComponent<ProjectileController>(), position, rotation);
            projectileToUse.transform.parent = projectileParent;
            _activeProjectiles.Add(projectileToUse);
        }

        projectileToUse.InitialiseProjectile(position, rotation); //Reset the projectile
    }


    public void SpawnTurretProjectile(Transform prefab, Vector3 position, Quaternion rotation)
    {
        ProjectileController projectileToUse = null;

        foreach (ProjectileController projectile in _activeTurretProjectiles) //Reuse projectile (avoids uneccessary use of memory)
        {
            if (!projectile.gameObject.activeSelf)
            {
                projectile.gameObject.SetActive(true);
                projectileToUse = projectile;
                break;
            }
        }

        if (projectileToUse == null) //Projectile not found, create a new one
        {
            projectileToUse = Instantiate(prefab.GetComponent<ProjectileController>(), position, rotation);
            projectileToUse.transform.parent = projectileParent;
            _activeTurretProjectiles.Add(projectileToUse);
        }

        projectileToUse.InitialiseProjectile(position, rotation); //Reset the projectile
    }

    public ProjectileController SpawnSeekerProjectile(Transform prefab, Vector3 position, Quaternion rotation)
    {
        ProjectileController projectileToUse = null;

        foreach (ProjectileController projectile in _seekerProjectiles) //Reuse projectile (avoids uneccessary use of memory)
        {
            if (!projectile.gameObject.activeSelf)
            {
                projectile.gameObject.SetActive(true);
                projectileToUse = projectile;
                break;
            }
        }

        if (projectileToUse == null) //Projectile not found, create a new one
        {
            projectileToUse = Instantiate(prefab.GetComponent<ProjectileController>(), position, rotation);
            projectileToUse.transform.parent = projectileParent;
            _seekerProjectiles.Add(projectileToUse);
        }

        projectileToUse.InitialiseProjectile(position, rotation); //Reset the projectile

        return projectileToUse;
    }

    public void SpawnEnemy(SpawnSettings spawnSettings)
    {
        EnemyEntity enemyEntity = null;

        foreach(EnemyEntity enemy in enemyList)
        {
            if(!enemy.gameObject.activeSelf)
            {
                if(enemy.EnemyTypeRef == spawnSettings.EnemyTypeToSpawn) //Is the same enemy, and is inactive, then use this enemy object for the new enemy
                {
                    enemy.gameObject.SetActive(true);
                    enemyEntity = enemy;
                    break;
                }
            }
        }

        //Spawn settings
        int spawnIndex = spawnSettings.SpawnLocationIndex;
        Transform spawnPos = spawnArray[spawnIndex];
        Transform initialTargetPos = spawnPos.GetChild(0);
        Animator door = doorAnimators[spawnIndex];


        if (enemyEntity == null) //An inactive enemy was not found, so instantiate a new enemy object
        {
            enemyEntity = Instantiate(enemyPrefabs[(int)spawnSettings.EnemyTypeToSpawn].GetComponent<EnemyEntity>(), spawnPos.position, spawnPos.rotation);
            enemyEntity.transform.parent = enemyParent;
            enemyList.Add(enemyEntity);
        }

        enemyEntity.ResetEnemy(spawnPos.position); //Resets the enemy properties to their default state
        enemyEntity.InitialTargetLocation = initialTargetPos;

        door.SetBool("open", true); //Opens the door. The door will be open until it is closed by this enemy when it reaches the inital target location
        enemyEntity.DoorAnimator = door; //Assigns the door animator to the enemy for later

        activeHostiles++;
    }

}
