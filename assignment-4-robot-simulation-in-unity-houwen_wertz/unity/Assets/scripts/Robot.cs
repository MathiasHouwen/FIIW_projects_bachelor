using UnityEngine;

public class Robot : MonoBehaviour
{
    public Transform horizontalBeam;
    public Transform verticalBeam;
    private RobotMovement movement;

    private enum State { None, PickingUP, DroppingOff }
    private State currentState = State.None;

    private GameObject block = null;
    private Transform targetParent = null;

    private Vector3 targetPosition = new Vector3(0,0,0);

    private System.Action onCompleteCallback = null;

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

    public void MoveBlock(GameObject block, Transform targetParent, Vector3 targetPosition, System.Action onCompleteCallback)
    {
        currentState = State.PickingUP;
        this.targetParent = targetParent;
        this.block = block;
        this.targetPosition = targetPosition;
        this.onCompleteCallback = onCompleteCallback;
        MoveTo(block.transform.position);
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
        if (currentState == State.PickingUP)
        {
            block.transform.SetParent(verticalBeam);
            makeBlockStick(block, true);
            currentState = State.DroppingOff;
            MoveTo(targetPosition);
        }
        else if (currentState == State.DroppingOff)
        {
            currentState = State.None;
            block.transform.SetParent(targetParent);
            makeBlockStick(block, false);
            onCompleteCallback?.Invoke();
            onCompleteCallback = null;
        }
    }


    private void makeBlockStick(GameObject block, bool stick)
    {
        Rigidbody rb = block.GetComponent<Rigidbody>();
        if (rb != null)
        {
            rb.isKinematic = stick;
            rb.useGravity = !stick;
        }
    }
}
