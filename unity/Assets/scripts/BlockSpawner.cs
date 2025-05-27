using UnityEngine;

public class BlockSpawner : MonoBehaviour
{
    public GameObject blockObjectPrefab;
    public Transform spawnPoint;

    public Transform parentBin;
    public float randomOffset = 0.2f;

    public void SpawnCube()
    {
        Vector3 randomOffsetVector = new Vector3(
           Random.Range(-randomOffset, randomOffset),
           0f,
           Random.Range(-randomOffset, randomOffset)
       );
        GameObject block = Instantiate(blockObjectPrefab, spawnPoint.position + randomOffsetVector, Quaternion.identity);
        block.transform.SetParent(parentBin);
    }
}
