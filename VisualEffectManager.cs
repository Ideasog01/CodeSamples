using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.VFX;

public class VisualEffectManager : MonoBehaviour
{
    public void StartVFX(VisualEffect visualEffect)
    {
        if(visualEffect.VFXSystem != null)
        {
            visualEffect.VFXSystem.Play();
        }
        else
        {
            if(visualEffect.VFXPrefab != null)
            {
                visualEffect.VFXSystem = Instantiate(visualEffect.VFXPrefab.GetComponent<ParticleSystem>(), visualEffect.SpawnPos.position, visualEffect.SpawnPos.rotation);
            }
        }
        
        if(visualEffect.VFXDuration != 0)
        {
            StartCoroutine(DelayVFXStop(visualEffect));
        }
        
    }

    public void StopVFX(VisualEffect visualEffect)
    {
        if(visualEffect.VFXSystem != null)
        {
            visualEffect.VFXSystem.Stop();
        }
    }

    private IEnumerator DelayVFXStop(VisualEffect visualEffect)
    {
        yield return new WaitForSeconds(visualEffect.VFXDuration);
        visualEffect.VFXSystem.Stop();
    }
}

[System.Serializable]
public struct VisualEffect
{
    [SerializeField]
    private Transform vfxPrefab;

    [SerializeField]
    private ParticleSystem vfxSystem;

    [SerializeField]
    private Transform spawnPos;

    [SerializeField]
    private float vfxDuration;

    public Transform VFXPrefab
    {
        get { return vfxPrefab; }
    }

    public ParticleSystem VFXSystem
    {
        get { return vfxSystem; }
        set { vfxSystem = value; }
    }

    public Transform SpawnPos
    {
        get { return spawnPos; }
    }

    public float VFXDuration
    {
        get { return vfxDuration; }
    }
}
