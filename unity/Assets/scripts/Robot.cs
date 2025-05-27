using UnityEngine;

public class Robot : MonoBehaviour
{
    public Transform horizontalBeam;
    public Transform verticalBeam;

    private RobotMovement movement;

    // override
    public void Start()
    {
        if (horizontalBeam == null || verticalBeam == null)
        {
            Debug.LogWarning("Please assign horizontal and vertical beams in the inspector.");
        }

        movement = GetComponent<RobotMovement>();
        if (movement == null)
        {
            Debug.LogError("RobotMovement component not found on Robot.");
            return;
        }

        movement.OnMovementComplete += OnMoveComplete;
    }

    // override
    public void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            MoveTo(new Vector3(2f, 0.5f, 3f));
        }
    }

    public void MoveToTransform(Transform target)
    {
        MoveTo(target.position);
    }

    public void MoveTo(Vector3 target)
    {
        if (movement != null)
        {
            movement.MoveTipTo(target);
        }
    }

    private void OnMoveComplete()
    {
        Debug.Log("✅ Robot finished moving to the target!");
    }
}
